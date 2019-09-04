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
typedef  size_t u32 ;
struct hwq {int dummy; } ;
struct afu {struct hwq* hwqs; } ;

/* Variables and functions */
 size_t CXLFLASH_MAX_HWQS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline struct hwq *get_hwq(struct afu *afu, u32 index)
{
	WARN_ON(index >= CXLFLASH_MAX_HWQS);

	return &afu->hwqs[index];
}