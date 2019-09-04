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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ EXTRACT_BIT_SET (int /*<<< orphan*/ ,char) ; 
 scalar_t__ MDP_HDR_LEN ; 
 int /*<<< orphan*/  PMS_FIFONO ; 
 scalar_t__ PMS_FIFONO_MDP ; 
 int /*<<< orphan*/  PMS_TELID ; 
 scalar_t__ PMS_TELID_UNSEGM_MAMAC ; 

__attribute__((used)) static inline bool pms_is_mamac(char *buf, u32 len)
{
	return (len > MDP_HDR_LEN &&
		EXTRACT_BIT_SET(PMS_FIFONO, buf[3]) == PMS_FIFONO_MDP &&
		EXTRACT_BIT_SET(PMS_TELID, buf[14]) == PMS_TELID_UNSEGM_MAMAC);
}