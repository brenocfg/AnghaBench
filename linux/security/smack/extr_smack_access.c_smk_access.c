#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smk_audit_info {int dummy; } ;
struct smack_known {scalar_t__ smk_known; int /*<<< orphan*/  smk_rules; } ;

/* Variables and functions */
 int EACCES ; 
 int MAY_ANYREAD ; 
 int MAY_BRINGUP ; 
 int MAY_LOCK ; 
 int MAY_NOT ; 
 int SMACK_BRINGUP_ALLOW ; 
 int SMACK_UNCONFINED_OBJECT ; 
 int SMACK_UNCONFINED_SUBJECT ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smack_known smack_known_floor ; 
 struct smack_known smack_known_hat ; 
 struct smack_known smack_known_star ; 
 struct smack_known smack_known_web ; 
 int /*<<< orphan*/  smack_log (scalar_t__,scalar_t__,int,int,struct smk_audit_info*) ; 
 struct smack_known* smack_unconfined ; 
 int smk_access_entry (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

int smk_access(struct smack_known *subject, struct smack_known *object,
	       int request, struct smk_audit_info *a)
{
	int may = MAY_NOT;
	int rc = 0;

	/*
	 * Hardcoded comparisons.
	 */
	/*
	 * A star subject can't access any object.
	 */
	if (subject == &smack_known_star) {
		rc = -EACCES;
		goto out_audit;
	}
	/*
	 * An internet object can be accessed by any subject.
	 * Tasks cannot be assigned the internet label.
	 * An internet subject can access any object.
	 */
	if (object == &smack_known_web || subject == &smack_known_web)
		goto out_audit;
	/*
	 * A star object can be accessed by any subject.
	 */
	if (object == &smack_known_star)
		goto out_audit;
	/*
	 * An object can be accessed in any way by a subject
	 * with the same label.
	 */
	if (subject->smk_known == object->smk_known)
		goto out_audit;
	/*
	 * A hat subject can read or lock any object.
	 * A floor object can be read or locked by any subject.
	 */
	if ((request & MAY_ANYREAD) == request ||
	    (request & MAY_LOCK) == request) {
		if (object == &smack_known_floor)
			goto out_audit;
		if (subject == &smack_known_hat)
			goto out_audit;
	}
	/*
	 * Beyond here an explicit relationship is required.
	 * If the requested access is contained in the available
	 * access (e.g. read is included in readwrite) it's
	 * good. A negative response from smk_access_entry()
	 * indicates there is no entry for this pair.
	 */
	rcu_read_lock();
	may = smk_access_entry(subject->smk_known, object->smk_known,
			       &subject->smk_rules);
	rcu_read_unlock();

	if (may <= 0 || (request & may) != request) {
		rc = -EACCES;
		goto out_audit;
	}
#ifdef CONFIG_SECURITY_SMACK_BRINGUP
	/*
	 * Return a positive value if using bringup mode.
	 * This allows the hooks to identify checks that
	 * succeed because of "b" rules.
	 */
	if (may & MAY_BRINGUP)
		rc = SMACK_BRINGUP_ALLOW;
#endif

out_audit:

#ifdef CONFIG_SECURITY_SMACK_BRINGUP
	if (rc < 0) {
		if (object == smack_unconfined)
			rc = SMACK_UNCONFINED_OBJECT;
		if (subject == smack_unconfined)
			rc = SMACK_UNCONFINED_SUBJECT;
	}
#endif

#ifdef CONFIG_AUDIT
	if (a)
		smack_log(subject->smk_known, object->smk_known,
			  request, rc, a);
#endif

	return rc;
}