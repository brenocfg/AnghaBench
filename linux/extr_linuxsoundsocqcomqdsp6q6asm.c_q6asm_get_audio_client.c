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
struct q6asm {int /*<<< orphan*/  slock; struct audio_client** session; int /*<<< orphan*/  dev; } ;
struct audio_client {int session; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int MAX_SESSIONS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct audio_client *q6asm_get_audio_client(struct q6asm *a,
						   int session_id)
{
	struct audio_client *ac = NULL;
	unsigned long flags;

	spin_lock_irqsave(&a->slock, flags);
	if ((session_id <= 0) || (session_id > MAX_SESSIONS)) {
		dev_err(a->dev, "invalid session: %d\n", session_id);
		goto err;
	}

	/* check for valid session */
	if (!a->session[session_id])
		goto err;
	else if (a->session[session_id]->session != session_id)
		goto err;

	ac = a->session[session_id];
	kref_get(&ac->refcount);
err:
	spin_unlock_irqrestore(&a->slock, flags);
	return ac;
}