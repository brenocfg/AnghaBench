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
struct ath_regulatory {int country_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ATH_REG_DYNAMIC_USER_CERT_TESTING ; 
#define  CTRY_JAPAN1 187 
#define  CTRY_JAPAN10 186 
#define  CTRY_JAPAN11 185 
#define  CTRY_JAPAN12 184 
#define  CTRY_JAPAN13 183 
#define  CTRY_JAPAN14 182 
#define  CTRY_JAPAN15 181 
#define  CTRY_JAPAN16 180 
#define  CTRY_JAPAN17 179 
#define  CTRY_JAPAN18 178 
#define  CTRY_JAPAN19 177 
#define  CTRY_JAPAN2 176 
#define  CTRY_JAPAN20 175 
#define  CTRY_JAPAN21 174 
#define  CTRY_JAPAN22 173 
#define  CTRY_JAPAN23 172 
#define  CTRY_JAPAN24 171 
#define  CTRY_JAPAN25 170 
#define  CTRY_JAPAN26 169 
#define  CTRY_JAPAN27 168 
#define  CTRY_JAPAN28 167 
#define  CTRY_JAPAN29 166 
#define  CTRY_JAPAN3 165 
#define  CTRY_JAPAN30 164 
#define  CTRY_JAPAN31 163 
#define  CTRY_JAPAN32 162 
#define  CTRY_JAPAN33 161 
#define  CTRY_JAPAN34 160 
#define  CTRY_JAPAN35 159 
#define  CTRY_JAPAN36 158 
#define  CTRY_JAPAN37 157 
#define  CTRY_JAPAN38 156 
#define  CTRY_JAPAN39 155 
#define  CTRY_JAPAN4 154 
#define  CTRY_JAPAN40 153 
#define  CTRY_JAPAN41 152 
#define  CTRY_JAPAN42 151 
#define  CTRY_JAPAN43 150 
#define  CTRY_JAPAN44 149 
#define  CTRY_JAPAN45 148 
#define  CTRY_JAPAN46 147 
#define  CTRY_JAPAN47 146 
#define  CTRY_JAPAN48 145 
#define  CTRY_JAPAN49 144 
#define  CTRY_JAPAN5 143 
#define  CTRY_JAPAN50 142 
#define  CTRY_JAPAN51 141 
#define  CTRY_JAPAN52 140 
#define  CTRY_JAPAN53 139 
#define  CTRY_JAPAN54 138 
#define  CTRY_JAPAN55 137 
#define  CTRY_JAPAN56 136 
#define  CTRY_JAPAN57 135 
#define  CTRY_JAPAN58 134 
#define  CTRY_JAPAN59 133 
#define  CTRY_JAPAN6 132 
#define  CTRY_JAPAN7 131 
#define  CTRY_JAPAN8 130 
#define  CTRY_JAPAN9 129 
#define  CTRY_UNITED_STATES 128 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dynamic_country_user_possible(struct ath_regulatory *reg)
{
	if (IS_ENABLED(CONFIG_ATH_REG_DYNAMIC_USER_CERT_TESTING))
		return true;

	switch (reg->country_code) {
	case CTRY_UNITED_STATES:
	case CTRY_JAPAN1:
	case CTRY_JAPAN2:
	case CTRY_JAPAN3:
	case CTRY_JAPAN4:
	case CTRY_JAPAN5:
	case CTRY_JAPAN6:
	case CTRY_JAPAN7:
	case CTRY_JAPAN8:
	case CTRY_JAPAN9:
	case CTRY_JAPAN10:
	case CTRY_JAPAN11:
	case CTRY_JAPAN12:
	case CTRY_JAPAN13:
	case CTRY_JAPAN14:
	case CTRY_JAPAN15:
	case CTRY_JAPAN16:
	case CTRY_JAPAN17:
	case CTRY_JAPAN18:
	case CTRY_JAPAN19:
	case CTRY_JAPAN20:
	case CTRY_JAPAN21:
	case CTRY_JAPAN22:
	case CTRY_JAPAN23:
	case CTRY_JAPAN24:
	case CTRY_JAPAN25:
	case CTRY_JAPAN26:
	case CTRY_JAPAN27:
	case CTRY_JAPAN28:
	case CTRY_JAPAN29:
	case CTRY_JAPAN30:
	case CTRY_JAPAN31:
	case CTRY_JAPAN32:
	case CTRY_JAPAN33:
	case CTRY_JAPAN34:
	case CTRY_JAPAN35:
	case CTRY_JAPAN36:
	case CTRY_JAPAN37:
	case CTRY_JAPAN38:
	case CTRY_JAPAN39:
	case CTRY_JAPAN40:
	case CTRY_JAPAN41:
	case CTRY_JAPAN42:
	case CTRY_JAPAN43:
	case CTRY_JAPAN44:
	case CTRY_JAPAN45:
	case CTRY_JAPAN46:
	case CTRY_JAPAN47:
	case CTRY_JAPAN48:
	case CTRY_JAPAN49:
	case CTRY_JAPAN50:
	case CTRY_JAPAN51:
	case CTRY_JAPAN52:
	case CTRY_JAPAN53:
	case CTRY_JAPAN54:
	case CTRY_JAPAN55:
	case CTRY_JAPAN56:
	case CTRY_JAPAN57:
	case CTRY_JAPAN58:
	case CTRY_JAPAN59:
		return false;
	}

	return true;
}