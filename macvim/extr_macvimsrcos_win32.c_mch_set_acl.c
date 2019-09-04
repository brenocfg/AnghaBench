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
typedef  int /*<<< orphan*/  vim_acl_T ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */

void
mch_set_acl(char_u *fname, vim_acl_T acl)
{
#ifdef HAVE_ACL
    struct my_acl   *p = (struct my_acl *)acl;
    SECURITY_INFORMATION    sec_info = 0;

    if (p != NULL && advapi_lib != NULL)
    {
# ifdef FEAT_MBYTE
	WCHAR	*wn = NULL;
# endif

	/* Set security flags */
	if (p->pSidOwner)
	    sec_info |= OWNER_SECURITY_INFORMATION;
	if (p->pSidGroup)
	    sec_info |= GROUP_SECURITY_INFORMATION;
	if (p->pDacl)
	{
	    sec_info |= DACL_SECURITY_INFORMATION;
	    /* Do not inherit its parent's DACL.
	     * If the DACL is inherited, Cygwin permissions would be changed.
	     */
	    if (!is_acl_inherited(p->pDacl))
		sec_info |= PROTECTED_DACL_SECURITY_INFORMATION;
	}
	if (p->pSacl)
	    sec_info |= SACL_SECURITY_INFORMATION;

# ifdef FEAT_MBYTE
	if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
	    wn = enc_to_utf16(fname, NULL);
	if (wn != NULL)
	{
	    (void)pSetNamedSecurityInfoW(
			wn,			// Abstract filename
			SE_FILE_OBJECT,		// File Object
			sec_info,
			p->pSidOwner,		// Ownership information.
			p->pSidGroup,		// Group membership.
			p->pDacl,		// Discretionary information.
			p->pSacl		// For auditing purposes.
			);
	    vim_free(wn);
	}
	else
# endif
	{
	    (void)pSetNamedSecurityInfo(
			(LPSTR)fname,		// Abstract filename
			SE_FILE_OBJECT,		// File Object
			sec_info,
			p->pSidOwner,		// Ownership information.
			p->pSidGroup,		// Group membership.
			p->pDacl,		// Discretionary information.
			p->pSacl		// For auditing purposes.
			);
	}
    }
#endif
}