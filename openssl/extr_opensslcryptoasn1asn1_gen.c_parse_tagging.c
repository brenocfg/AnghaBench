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
 int /*<<< orphan*/  ASN1_F_PARSE_TAGGING ; 
 int /*<<< orphan*/  ASN1_R_INVALID_MODIFIER ; 
 int /*<<< orphan*/  ASN1_R_INVALID_NUMBER ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char*) ; 
 int V_ASN1_APPLICATION ; 
 int V_ASN1_CONTEXT_SPECIFIC ; 
 int V_ASN1_PRIVATE ; 
 int V_ASN1_UNIVERSAL ; 
 long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int parse_tagging(const char *vstart, int vlen, int *ptag, int *pclass)
{
    char erch[2];
    long tag_num;
    char *eptr;
    if (!vstart)
        return 0;
    tag_num = strtoul(vstart, &eptr, 10);
    /* Check we haven't gone past max length: should be impossible */
    if (eptr && *eptr && (eptr > vstart + vlen))
        return 0;
    if (tag_num < 0) {
        ASN1err(ASN1_F_PARSE_TAGGING, ASN1_R_INVALID_NUMBER);
        return 0;
    }
    *ptag = tag_num;
    /* If we have non numeric characters, parse them */
    if (eptr)
        vlen -= eptr - vstart;
    else
        vlen = 0;
    if (vlen) {
        switch (*eptr) {

        case 'U':
            *pclass = V_ASN1_UNIVERSAL;
            break;

        case 'A':
            *pclass = V_ASN1_APPLICATION;
            break;

        case 'P':
            *pclass = V_ASN1_PRIVATE;
            break;

        case 'C':
            *pclass = V_ASN1_CONTEXT_SPECIFIC;
            break;

        default:
            erch[0] = *eptr;
            erch[1] = 0;
            ASN1err(ASN1_F_PARSE_TAGGING, ASN1_R_INVALID_MODIFIER);
            ERR_add_error_data(2, "Char=", erch);
            return 0;

        }
    } else
        *pclass = V_ASN1_CONTEXT_SPECIFIC;

    return 1;

}