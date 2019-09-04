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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_DEV (struct device*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int NVM_CHANNEL_160MHZ ; 
 int NVM_CHANNEL_20MHZ ; 
 int NVM_CHANNEL_40MHZ ; 
 int NVM_CHANNEL_80MHZ ; 
 int NVM_CHANNEL_ACTIVE ; 
 int NVM_CHANNEL_DC_HIGH ; 
 int NVM_CHANNEL_GO_CONCURRENT ; 
 int NVM_CHANNEL_IBSS ; 
 int NVM_CHANNEL_INDOOR_ONLY ; 
 int NVM_CHANNEL_RADAR ; 
 int NVM_CHANNEL_UNIFORM ; 
 int NVM_CHANNEL_VALID ; 

__attribute__((used)) static inline void iwl_nvm_print_channel_flags(struct device *dev, u32 level,
					       int chan, u16 flags)
{
#define CHECK_AND_PRINT_I(x)	\
	((flags & NVM_CHANNEL_##x) ? " " #x : "")

	if (!(flags & NVM_CHANNEL_VALID)) {
		IWL_DEBUG_DEV(dev, level, "Ch. %d: 0x%x: No traffic\n",
			      chan, flags);
		return;
	}

	/* Note: already can print up to 101 characters, 110 is the limit! */
	IWL_DEBUG_DEV(dev, level,
		      "Ch. %d: 0x%x:%s%s%s%s%s%s%s%s%s%s%s%s\n",
		      chan, flags,
		      CHECK_AND_PRINT_I(VALID),
		      CHECK_AND_PRINT_I(IBSS),
		      CHECK_AND_PRINT_I(ACTIVE),
		      CHECK_AND_PRINT_I(RADAR),
		      CHECK_AND_PRINT_I(INDOOR_ONLY),
		      CHECK_AND_PRINT_I(GO_CONCURRENT),
		      CHECK_AND_PRINT_I(UNIFORM),
		      CHECK_AND_PRINT_I(20MHZ),
		      CHECK_AND_PRINT_I(40MHZ),
		      CHECK_AND_PRINT_I(80MHZ),
		      CHECK_AND_PRINT_I(160MHZ),
		      CHECK_AND_PRINT_I(DC_HIGH));
#undef CHECK_AND_PRINT_I
}