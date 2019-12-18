#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t length; scalar_t__ data; } ;
typedef  TYPE_1__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_grow (TYPE_1__*,size_t) ; 
 TYPE_1__* BUF_MEM_new () ; 
 int /*<<< orphan*/  ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 

__attribute__((used)) static int collect(BUF_MEM **collector, void *data, size_t datalen)
{
    size_t i;

    if (*collector == NULL)
        *collector = BUF_MEM_new();
    if (*collector == NULL) {
        ERR_raise(ERR_LIB_EVP, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if (data != NULL && datalen > 0) {
        i = (*collector)->length; /* BUF_MEM_grow() changes it! */

        if (!BUF_MEM_grow(*collector, i + datalen))
            return 0;
        memcpy((*collector)->data + i, data, datalen);
    }
    return 1;
}