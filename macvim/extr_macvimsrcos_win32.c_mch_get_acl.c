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

vim_acl_T
mch_get_acl(char_u *fname)
{
#ifndef HAVE_ACL
    return (vim_acl_T)NULL;
#else
    struct my_acl   *p = NULL;
    DWORD   err;

    /* This only works on Windows NT and 2000. */
    if (g_PlatformId == VER_PLATFORM_WIN32_NT && advapi_lib != NULL)
    {
	p = (struct my_acl *)alloc_clear((unsigned)sizeof(struct my_acl));
	if (p != NULL)
	{
# ifdef FEAT_MBYTE
	    WCHAR	*wn = NULL;

	    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
		wn = enc_to_utf16(fname, NULL);
	    if (wn != NULL)
	    {
		/* Try to retrieve the entire security descriptor. */
		err = pGetNamedSecurityInfoW(
			    wn,			// Abstract filename
			    SE_FILE_OBJECT,	// File Object
			    OWNER_SECURITY_INFORMATION |
			    GROUP_SECURITY_INFORMATION |
			    DACL_SECURITY_INFORMATION |
			    SACL_SECURITY_INFORMATION,
			    &p->pSidOwner,	// Ownership information.
			    &p->pSidGroup,	// Group membership.
			    &p->pDacl,		// Discretionary information.
			    &p->pSacl,		// For auditing purposes.
			    &p->pSecurityDescriptor);
		if (err == ERROR_ACCESS_DENIED ||
			err == ERROR_PRIVILEGE_NOT_HELD)
		{
		    /* Retrieve only DACL. */
		    (void)pGetNamedSecurityInfoW(
			    wn,
			    SE_FILE_OBJECT,
			    DACL_SECURITY_INFORMATION,
			    NULL,
			    NULL,
			    &p->pDacl,
			    NULL,
			    &p->pSecurityDescriptor);
		}
		if (p->pSecurityDescriptor == NULL)
		{
		    mch_free_acl((vim_acl_T)p);
		    p = NULL;
		}
		vim_free(wn);
	    }
	    else
# endif
	    {
		/* Try to retrieve the entire security descriptor. */
		err = pGetNamedSecurityInfo(
			    (LPSTR)fname,	// Abstract filename
			    SE_FILE_OBJECT,	// File Object
			    OWNER_SECURITY_INFORMATION |
			    GROUP_SECURITY_INFORMATION |
			    DACL_SECURITY_INFORMATION |
			    SACL_SECURITY_INFORMATION,
			    &p->pSidOwner,	// Ownership information.
			    &p->pSidGroup,	// Group membership.
			    &p->pDacl,		// Discretionary information.
			    &p->pSacl,		// For auditing purposes.
			    &p->pSecurityDescriptor);
		if (err == ERROR_ACCESS_DENIED ||
			err == ERROR_PRIVILEGE_NOT_HELD)
		{
		    /* Retrieve only DACL. */
		    (void)pGetNamedSecurityInfo(
			    (LPSTR)fname,
			    SE_FILE_OBJECT,
			    DACL_SECURITY_INFORMATION,
			    NULL,
			    NULL,
			    &p->pDacl,
			    NULL,
			    &p->pSecurityDescriptor);
		}
		if (p->pSecurityDescriptor == NULL)
		{
		    mch_free_acl((vim_acl_T)p);
		    p = NULL;
		}
	    }
	}
    }

    return (vim_acl_T)p;
#endif
}