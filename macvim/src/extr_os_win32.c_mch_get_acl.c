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
struct my_acl {int /*<<< orphan*/ * pSecurityDescriptor; int /*<<< orphan*/  pDacl; int /*<<< orphan*/  pSacl; int /*<<< orphan*/  pSidGroup; int /*<<< orphan*/  pSidOwner; } ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int DACL_SECURITY_INFORMATION ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_PRIVILEGE_NOT_HELD ; 
 int GROUP_SECURITY_INFORMATION ; 
 scalar_t__ GetACP () ; 
 int OWNER_SECURITY_INFORMATION ; 
 int SACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  SE_FILE_OBJECT ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 int /*<<< orphan*/ * advapi_lib ; 
 scalar_t__ alloc_clear (unsigned int) ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_PlatformId ; 
 int /*<<< orphan*/  mch_free_acl (int /*<<< orphan*/ ) ; 
 scalar_t__ pGetNamedSecurityInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ pGetNamedSecurityInfoW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

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