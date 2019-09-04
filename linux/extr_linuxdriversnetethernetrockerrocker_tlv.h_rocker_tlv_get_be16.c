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
struct rocker_tlv {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ rocker_tlv_data (struct rocker_tlv const*) ; 

__attribute__((used)) static inline __be16 rocker_tlv_get_be16(const struct rocker_tlv *tlv)
{
	return *(__be16 *) rocker_tlv_data(tlv);
}