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
 unsigned int MS_PVKMAGIC ; 
 int /*<<< orphan*/  PEM_F_DO_PVK_HEADER ; 
 int /*<<< orphan*/  PEM_R_BAD_MAGIC_NUMBER ; 
 int /*<<< orphan*/  PEM_R_INCONSISTENT_HEADER ; 
 int /*<<< orphan*/  PEM_R_PVK_TOO_SHORT ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int PVK_MAX_KEYLEN ; 
 unsigned int PVK_MAX_SALTLEN ; 
 unsigned int read_ledword (unsigned char const**) ; 

__attribute__((used)) static int do_PVK_header(const unsigned char **in, unsigned int length,
                         int skip_magic,
                         unsigned int *psaltlen, unsigned int *pkeylen)
{
    const unsigned char *p = *in;
    unsigned int pvk_magic, is_encrypted;

    if (skip_magic) {
        if (length < 20) {
            PEMerr(PEM_F_DO_PVK_HEADER, PEM_R_PVK_TOO_SHORT);
            return 0;
        }
    } else {
        if (length < 24) {
            PEMerr(PEM_F_DO_PVK_HEADER, PEM_R_PVK_TOO_SHORT);
            return 0;
        }
        pvk_magic = read_ledword(&p);
        if (pvk_magic != MS_PVKMAGIC) {
            PEMerr(PEM_F_DO_PVK_HEADER, PEM_R_BAD_MAGIC_NUMBER);
            return 0;
        }
    }
    /* Skip reserved */
    p += 4;
    /*
     * keytype =
     */ read_ledword(&p);
    is_encrypted = read_ledword(&p);
    *psaltlen = read_ledword(&p);
    *pkeylen = read_ledword(&p);

    if (*pkeylen > PVK_MAX_KEYLEN || *psaltlen > PVK_MAX_SALTLEN)
        return 0;

    if (is_encrypted && *psaltlen == 0) {
        PEMerr(PEM_F_DO_PVK_HEADER, PEM_R_INCONSISTENT_HEADER);
        return 0;
    }

    *in = p;
    return 1;
}