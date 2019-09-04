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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_gige {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SSB_GIGE_PCICFG ; 
 int /*<<< orphan*/  gige_read16 (struct ssb_gige*,scalar_t__) ; 

__attribute__((used)) static inline
u16 gige_pcicfg_read16(struct ssb_gige *dev, unsigned int offset)
{
	BUG_ON(offset >= 256);
	return gige_read16(dev, SSB_GIGE_PCICFG + offset);
}