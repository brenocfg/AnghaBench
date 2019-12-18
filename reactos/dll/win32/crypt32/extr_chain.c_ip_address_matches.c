#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subnet ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_4__ {int cbData; int* pbData; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int CERT_TRUST_INVALID_NAME_CONSTRAINTS ; 
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int,int*,int,int*) ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static BOOL ip_address_matches(const CRYPT_DATA_BLOB *constraint,
 const CRYPT_DATA_BLOB *name, DWORD *trustErrorStatus)
{
    BOOL match = FALSE;

    TRACE("(%d, %p), (%d, %p)\n", constraint->cbData, constraint->pbData,
     name->cbData, name->pbData);

    /* RFC5280, section 4.2.1.10, iPAddress syntax: either 8 or 32 bytes, for
     * IPv4 or IPv6 addresses, respectively.
     */
    if (constraint->cbData != sizeof(DWORD) * 2 && constraint->cbData != 32)
        *trustErrorStatus |= CERT_TRUST_INVALID_NAME_CONSTRAINTS;
    else if (name->cbData == sizeof(DWORD) &&
     constraint->cbData == sizeof(DWORD) * 2)
    {
        DWORD subnet, mask, addr;

        memcpy(&subnet, constraint->pbData, sizeof(subnet));
        memcpy(&mask, constraint->pbData + sizeof(subnet), sizeof(mask));
        memcpy(&addr, name->pbData, sizeof(addr));
        /* These are really in big-endian order, but for equality matching we
         * don't need to swap to host order
         */
        match = (subnet & mask) == (addr & mask);
    }
    else if (name->cbData == 16 && constraint->cbData == 32)
    {
        const BYTE *subnet, *mask, *addr;
        DWORD i;

        subnet = constraint->pbData;
        mask = constraint->pbData + 16;
        addr = name->pbData;
        match = TRUE;
        for (i = 0; match && i < 16; i++)
            if ((subnet[i] & mask[i]) != (addr[i] & mask[i]))
                match = FALSE;
    }
    /* else: name is wrong size, no match */

    return match;
}