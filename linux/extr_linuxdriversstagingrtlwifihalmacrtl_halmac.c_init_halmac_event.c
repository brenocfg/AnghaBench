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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
typedef  enum halmac_feature_id { ____Placeholder_halmac_feature_id } halmac_feature_id ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INDICATOR_TIMELMT ; 
 int init_halmac_event_with_waittime (struct rtl_priv*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int init_halmac_event(struct rtl_priv *rtlpriv,
				    enum halmac_feature_id id, u8 *buf,
				    u32 size)
{
	return init_halmac_event_with_waittime(rtlpriv, id, buf, size,
					       DEFAULT_INDICATOR_TIMELMT);
}