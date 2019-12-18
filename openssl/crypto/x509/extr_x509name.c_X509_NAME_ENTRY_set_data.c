#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* value; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ X509_NAME_ENTRY ;
struct TYPE_6__ {int type; } ;

/* Variables and functions */
 int ASN1_PRINTABLE_type (unsigned char const*,int) ; 
 int ASN1_STRING_set (TYPE_3__*,unsigned char const*,int) ; 
 scalar_t__ ASN1_STRING_set_by_NID (TYPE_3__**,unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 int MBSTRING_FLAG ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int V_ASN1_APP_CHOOSE ; 
 int V_ASN1_UNDEF ; 
 int strlen (char const*) ; 

int X509_NAME_ENTRY_set_data(X509_NAME_ENTRY *ne, int type,
                             const unsigned char *bytes, int len)
{
    int i;

    if ((ne == NULL) || ((bytes == NULL) && (len != 0)))
        return 0;
    if ((type > 0) && (type & MBSTRING_FLAG))
        return ASN1_STRING_set_by_NID(&ne->value, bytes,
                                      len, type,
                                      OBJ_obj2nid(ne->object)) ? 1 : 0;
    if (len < 0)
        len = strlen((const char *)bytes);
    i = ASN1_STRING_set(ne->value, bytes, len);
    if (!i)
        return 0;
    if (type != V_ASN1_UNDEF) {
        if (type == V_ASN1_APP_CHOOSE)
            ne->value->type = ASN1_PRINTABLE_type(bytes, len);
        else
            ne->value->type = type;
    }
    return 1;
}