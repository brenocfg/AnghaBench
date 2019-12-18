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
 int ASN1_GEN_FLAG ; 
 unsigned long ASN1_tag2bit (int) ; 
 unsigned long B_ASN1_DIRECTORYSTRING ; 
 int asn1_str2tag (char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int mask_cb(const char *elem, int len, void *arg)
{
    unsigned long *pmask = arg, tmpmask;
    int tag;
    if (elem == NULL)
        return 0;
    if ((len == 3) && (strncmp(elem, "DIR", 3) == 0)) {
        *pmask |= B_ASN1_DIRECTORYSTRING;
        return 1;
    }
    tag = asn1_str2tag(elem, len);
    if (!tag || (tag & ASN1_GEN_FLAG))
        return 0;
    tmpmask = ASN1_tag2bit(tag);
    if (!tmpmask)
        return 0;
    *pmask |= tmpmask;
    return 1;
}