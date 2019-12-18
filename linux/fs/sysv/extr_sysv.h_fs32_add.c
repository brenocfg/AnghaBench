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
struct sysv_sb_info {scalar_t__ s_bytesex; } ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __fs32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ BYTESEX_LE ; 
 scalar_t__ BYTESEX_PDP ; 
 scalar_t__ PDP_swab (scalar_t__) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline __fs32 fs32_add(struct sysv_sb_info *sbi, __fs32 *n, int d)
{
	if (sbi->s_bytesex == BYTESEX_PDP)
		*(__u32*)n = PDP_swab(PDP_swab(*(__u32*)n)+d);
	else if (sbi->s_bytesex == BYTESEX_LE)
		le32_add_cpu((__le32 *)n, d);
	else
		be32_add_cpu((__be32 *)n, d);
	return *n;
}