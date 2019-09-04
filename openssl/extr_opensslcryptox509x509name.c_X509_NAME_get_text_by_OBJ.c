#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 TYPE_1__* X509_NAME_ENTRY_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int X509_NAME_get_index_by_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int X509_NAME_get_text_by_OBJ(X509_NAME *name, const ASN1_OBJECT *obj,
                              char *buf, int len)
{
    int i;
    const ASN1_STRING *data;

    i = X509_NAME_get_index_by_OBJ(name, obj, -1);
    if (i < 0)
        return -1;
    data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, i));
    if (buf == NULL)
        return data->length;
    if (len <= 0)
        return 0;
    i = (data->length > (len - 1)) ? (len - 1) : data->length;
    memcpy(buf, data->data, i);
    buf[i] = '\0';
    return i;
}