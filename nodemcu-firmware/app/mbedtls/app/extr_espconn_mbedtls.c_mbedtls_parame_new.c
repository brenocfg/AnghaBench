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
typedef  int /*<<< orphan*/  uint8 ;
typedef  TYPE_1__* pmbedtls_parame ;
typedef  int /*<<< orphan*/  mbedtls_parame ;
struct TYPE_4__ {size_t parame_datalen; int /*<<< orphan*/ * parame_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 scalar_t__ os_zalloc (int) ; 

__attribute__((used)) static pmbedtls_parame mbedtls_parame_new(size_t capacity)
{
	pmbedtls_parame rb = (pmbedtls_parame)os_zalloc(sizeof(mbedtls_parame));
	if (rb && capacity != 0){
		rb->parame_datalen = capacity;
		rb->parame_data = (uint8*)os_zalloc(rb->parame_datalen + 1);
		if (rb->parame_data){

		} else{
			os_free(rb);
			rb = NULL;
		}
	}
	return rb;
}