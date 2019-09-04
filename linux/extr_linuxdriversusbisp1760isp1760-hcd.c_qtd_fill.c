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
struct isp1760_qtd {size_t length; void* data_buffer; } ;

/* Variables and functions */
 size_t MAX_PAYLOAD_SIZE ; 

__attribute__((used)) static int qtd_fill(struct isp1760_qtd *qtd, void *databuffer, size_t len)
{
	qtd->data_buffer = databuffer;

	if (len > MAX_PAYLOAD_SIZE)
		len = MAX_PAYLOAD_SIZE;
	qtd->length = len;

	return qtd->length;
}