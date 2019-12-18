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

/* Variables and functions */
#define  MS_DSS1MAGIC 131 
#define  MS_DSS2MAGIC 130 
 unsigned char const MS_PRIVATEKEYBLOB ; 
 unsigned char const MS_PUBLICKEYBLOB ; 
#define  MS_RSA1MAGIC 129 
#define  MS_RSA2MAGIC 128 
 int /*<<< orphan*/  PEM_F_DO_BLOB_HEADER ; 
 int /*<<< orphan*/  PEM_R_BAD_MAGIC_NUMBER ; 
 int /*<<< orphan*/  PEM_R_BAD_VERSION_NUMBER ; 
 int /*<<< orphan*/  PEM_R_EXPECTING_PRIVATE_KEY_BLOB ; 
 int /*<<< orphan*/  PEM_R_EXPECTING_PUBLIC_KEY_BLOB ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_ledword (unsigned char const**) ; 

__attribute__((used)) static int do_blob_header(const unsigned char **in, unsigned int length,
                          unsigned int *pmagic, unsigned int *pbitlen,
                          int *pisdss, int *pispub)
{
    const unsigned char *p = *in;
    if (length < 16)
        return 0;
    /* bType */
    if (*p == MS_PUBLICKEYBLOB) {
        if (*pispub == 0) {
            PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_EXPECTING_PRIVATE_KEY_BLOB);
            return 0;
        }
        *pispub = 1;
    } else if (*p == MS_PRIVATEKEYBLOB) {
        if (*pispub == 1) {
            PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_EXPECTING_PUBLIC_KEY_BLOB);
            return 0;
        }
        *pispub = 0;
    } else
        return 0;
    p++;
    /* Version */
    if (*p++ != 0x2) {
        PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_BAD_VERSION_NUMBER);
        return 0;
    }
    /* Ignore reserved, aiKeyAlg */
    p += 6;
    *pmagic = read_ledword(&p);
    *pbitlen = read_ledword(&p);
    *pisdss = 0;
    switch (*pmagic) {

    case MS_DSS1MAGIC:
        *pisdss = 1;
        /* fall thru */
    case MS_RSA1MAGIC:
        if (*pispub == 0) {
            PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_EXPECTING_PRIVATE_KEY_BLOB);
            return 0;
        }
        break;

    case MS_DSS2MAGIC:
        *pisdss = 1;
        /* fall thru */
    case MS_RSA2MAGIC:
        if (*pispub == 1) {
            PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_EXPECTING_PUBLIC_KEY_BLOB);
            return 0;
        }
        break;

    default:
        PEMerr(PEM_F_DO_BLOB_HEADER, PEM_R_BAD_MAGIC_NUMBER);
        return -1;
    }
    *in = p;
    return 1;
}