#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; TYPE_1__* key; } ;
struct TYPE_4__ {int id; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ FormatNode ;

/* Variables and functions */
#define  DCH_AD 197 
#define  DCH_AM 196 
#define  DCH_A_D 195 
#define  DCH_A_M 194 
#define  DCH_BC 193 
#define  DCH_B_C 192 
#define  DCH_CC 191 
#define  DCH_D 190 
 int DCH_DATED ; 
#define  DCH_DAY 189 
#define  DCH_DD 188 
#define  DCH_DDD 187 
#define  DCH_DY 186 
#define  DCH_Day 185 
#define  DCH_Dy 184 
#define  DCH_FF1 183 
#define  DCH_FF2 182 
#define  DCH_FF3 181 
#define  DCH_FF4 180 
#define  DCH_FF5 179 
#define  DCH_FF6 178 
#define  DCH_FX 177 
#define  DCH_HH 176 
#define  DCH_HH12 175 
#define  DCH_HH24 174 
#define  DCH_I 173 
#define  DCH_ID 172 
#define  DCH_IDDD 171 
#define  DCH_IY 170 
#define  DCH_IYY 169 
#define  DCH_IYYY 168 
#define  DCH_J 167 
#define  DCH_MI 166 
#define  DCH_MM 165 
#define  DCH_MON 164 
#define  DCH_MONTH 163 
#define  DCH_MS 162 
#define  DCH_Mon 161 
#define  DCH_Month 160 
#define  DCH_OF 159 
#define  DCH_PM 158 
#define  DCH_P_M 157 
#define  DCH_Q 156 
#define  DCH_RM 155 
#define  DCH_SS 154 
#define  DCH_SSSS 153 
 int DCH_TIMED ; 
#define  DCH_TZ 152 
#define  DCH_TZH 151 
#define  DCH_TZM 150 
#define  DCH_US 149 
#define  DCH_W 148 
#define  DCH_WW 147 
#define  DCH_Y 146 
#define  DCH_YY 145 
#define  DCH_YYY 144 
#define  DCH_YYYY 143 
#define  DCH_Y_YYY 142 
 int DCH_ZONED ; 
#define  DCH_a_d 141 
#define  DCH_a_m 140 
#define  DCH_ad 139 
#define  DCH_am 138 
#define  DCH_b_c 137 
#define  DCH_bc 136 
#define  DCH_day 135 
#define  DCH_dy 134 
#define  DCH_mon 133 
#define  DCH_month 132 
#define  DCH_p_m 131 
#define  DCH_pm 130 
#define  DCH_rm 129 
#define  DCH_tz 128 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ NODE_TYPE_ACTION ; 
 scalar_t__ NODE_TYPE_END ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
DCH_datetime_type(FormatNode *node, bool *have_error)
{
	FormatNode *n;
	int			flags = 0;

	for (n = node; n->type != NODE_TYPE_END; n++)
	{
		if (n->type != NODE_TYPE_ACTION)
			continue;

		switch (n->key->id)
		{
			case DCH_FX:
				break;
			case DCH_A_M:
			case DCH_P_M:
			case DCH_a_m:
			case DCH_p_m:
			case DCH_AM:
			case DCH_PM:
			case DCH_am:
			case DCH_pm:
			case DCH_HH:
			case DCH_HH12:
			case DCH_HH24:
			case DCH_MI:
			case DCH_SS:
			case DCH_MS:		/* millisecond */
			case DCH_US:		/* microsecond */
			case DCH_FF1:
			case DCH_FF2:
			case DCH_FF3:
			case DCH_FF4:
			case DCH_FF5:
			case DCH_FF6:
			case DCH_SSSS:
				flags |= DCH_TIMED;
				break;
			case DCH_tz:
			case DCH_TZ:
			case DCH_OF:
				RETURN_ERROR(ereport(ERROR,
									 (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
									  errmsg("formatting field \"%s\" is only supported in to_char",
											 n->key->name))));
				flags |= DCH_ZONED;
				break;
			case DCH_TZH:
			case DCH_TZM:
				flags |= DCH_ZONED;
				break;
			case DCH_A_D:
			case DCH_B_C:
			case DCH_a_d:
			case DCH_b_c:
			case DCH_AD:
			case DCH_BC:
			case DCH_ad:
			case DCH_bc:
			case DCH_MONTH:
			case DCH_Month:
			case DCH_month:
			case DCH_MON:
			case DCH_Mon:
			case DCH_mon:
			case DCH_MM:
			case DCH_DAY:
			case DCH_Day:
			case DCH_day:
			case DCH_DY:
			case DCH_Dy:
			case DCH_dy:
			case DCH_DDD:
			case DCH_IDDD:
			case DCH_DD:
			case DCH_D:
			case DCH_ID:
			case DCH_WW:
			case DCH_Q:
			case DCH_CC:
			case DCH_Y_YYY:
			case DCH_YYYY:
			case DCH_IYYY:
			case DCH_YYY:
			case DCH_IYY:
			case DCH_YY:
			case DCH_IY:
			case DCH_Y:
			case DCH_I:
			case DCH_RM:
			case DCH_rm:
			case DCH_W:
			case DCH_J:
				flags |= DCH_DATED;
				break;
		}
	}

on_error:
	return flags;
}