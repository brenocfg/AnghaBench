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

/* Variables and functions */
 int /*<<< orphan*/  rocker_tlv_data (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_len (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse (struct rocker_tlv const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rocker_tlv_parse_nested(const struct rocker_tlv **tb,
					   int maxtype,
					   const struct rocker_tlv *tlv)
{
	rocker_tlv_parse(tb, maxtype, rocker_tlv_data(tlv),
			 rocker_tlv_len(tlv));
}