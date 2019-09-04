#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xt_hmark_info {scalar_t__ proto_mask; scalar_t__ hoffset; int /*<<< orphan*/  hmodulus; int /*<<< orphan*/  hashrnd; } ;
struct TYPE_2__ {int /*<<< orphan*/  v32; } ;
struct hmark_tuple {scalar_t__ proto; TYPE_1__ uports; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ jhash_3words (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ reciprocal_scale (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32
hmark_hash(struct hmark_tuple *t, const struct xt_hmark_info *info)
{
	u32 hash;
	u32 src = ntohl(t->src);
	u32 dst = ntohl(t->dst);

	if (dst < src)
		swap(src, dst);

	hash = jhash_3words(src, dst, t->uports.v32, info->hashrnd);
	hash = hash ^ (t->proto & info->proto_mask);

	return reciprocal_scale(hash, info->hmodulus) + info->hoffset;
}