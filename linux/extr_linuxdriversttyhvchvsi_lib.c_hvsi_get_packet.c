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
struct hvsi_priv {size_t inbuf_len; int /*<<< orphan*/ * inbuf; int /*<<< orphan*/  termno; scalar_t__ (* get_chars ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 size_t HVSI_INBUF_SIZE ; 
 int hvsi_check_packet (struct hvsi_priv*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int hvsi_get_packet(struct hvsi_priv *pv)
{
	/* If we have room in the buffer, ask HV for more */
	if (pv->inbuf_len < HVSI_INBUF_SIZE)
		pv->inbuf_len += pv->get_chars(pv->termno,
					     &pv->inbuf[pv->inbuf_len],
					     HVSI_INBUF_SIZE - pv->inbuf_len);
	/*
	 * If we have at least 4 bytes in the buffer, check for
	 * a full packet and retry
	 */
	if (pv->inbuf_len >= 4)
		return hvsi_check_packet(pv);
	return 0;
}