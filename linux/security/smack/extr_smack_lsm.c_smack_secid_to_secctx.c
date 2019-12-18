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
typedef  int /*<<< orphan*/  u32 ;
struct smack_known {char* smk_known; } ;

/* Variables and functions */
 struct smack_known* smack_from_secid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int smack_secid_to_secctx(u32 secid, char **secdata, u32 *seclen)
{
	struct smack_known *skp = smack_from_secid(secid);

	if (secdata)
		*secdata = skp->smk_known;
	*seclen = strlen(skp->smk_known);
	return 0;
}