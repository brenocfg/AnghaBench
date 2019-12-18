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
typedef  scalar_t__ vim_acl_T ;
struct my_acl {int /*<<< orphan*/  pSecurityDescriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_free (struct my_acl*) ; 

void
mch_free_acl(vim_acl_T acl)
{
#ifdef HAVE_ACL
    struct my_acl   *p = (struct my_acl *)acl;

    if (p != NULL)
    {
	LocalFree(p->pSecurityDescriptor);	// Free the memory just in case
	vim_free(p);
    }
#endif
}