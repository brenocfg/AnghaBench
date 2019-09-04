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
struct rocker_tlv {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ROCKER_TLV_ALIGN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rocker_tlv *rocker_tlv_next(const struct rocker_tlv *tlv,
						 int *remaining)
{
	int totlen = ROCKER_TLV_ALIGN(tlv->len);

	*remaining -= totlen;
	return (struct rocker_tlv *) ((char *) tlv + totlen);
}