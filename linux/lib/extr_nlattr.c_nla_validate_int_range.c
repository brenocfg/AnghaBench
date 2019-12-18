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
struct nlattr {int dummy; } ;
struct nla_policy {scalar_t__ validation_type; int type; scalar_t__ min; scalar_t__ max; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
#define  NLA_S16 135 
#define  NLA_S32 134 
#define  NLA_S64 133 
#define  NLA_S8 132 
#define  NLA_U16 131 
#define  NLA_U32 130 
#define  NLA_U64 129 
#define  NLA_U8 128 
 scalar_t__ NLA_VALIDATE_MAX ; 
 scalar_t__ NLA_VALIDATE_MIN ; 
 scalar_t__ NLA_VALIDATE_RANGE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr const*,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ nla_get_s16 (struct nlattr const*) ; 
 scalar_t__ nla_get_s32 (struct nlattr const*) ; 
 scalar_t__ nla_get_s64 (struct nlattr const*) ; 
 scalar_t__ nla_get_s8 (struct nlattr const*) ; 
 scalar_t__ nla_get_u16 (struct nlattr const*) ; 
 scalar_t__ nla_get_u32 (struct nlattr const*) ; 
 scalar_t__ nla_get_u64 (struct nlattr const*) ; 
 scalar_t__ nla_get_u8 (struct nlattr const*) ; 

__attribute__((used)) static int nla_validate_int_range(const struct nla_policy *pt,
				  const struct nlattr *nla,
				  struct netlink_ext_ack *extack)
{
	bool validate_min, validate_max;
	s64 value;

	validate_min = pt->validation_type == NLA_VALIDATE_RANGE ||
		       pt->validation_type == NLA_VALIDATE_MIN;
	validate_max = pt->validation_type == NLA_VALIDATE_RANGE ||
		       pt->validation_type == NLA_VALIDATE_MAX;

	switch (pt->type) {
	case NLA_U8:
		value = nla_get_u8(nla);
		break;
	case NLA_U16:
		value = nla_get_u16(nla);
		break;
	case NLA_U32:
		value = nla_get_u32(nla);
		break;
	case NLA_S8:
		value = nla_get_s8(nla);
		break;
	case NLA_S16:
		value = nla_get_s16(nla);
		break;
	case NLA_S32:
		value = nla_get_s32(nla);
		break;
	case NLA_S64:
		value = nla_get_s64(nla);
		break;
	case NLA_U64:
		/* treat this one specially, since it may not fit into s64 */
		if ((validate_min && nla_get_u64(nla) < pt->min) ||
		    (validate_max && nla_get_u64(nla) > pt->max)) {
			NL_SET_ERR_MSG_ATTR(extack, nla,
					    "integer out of range");
			return -ERANGE;
		}
		return 0;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	if ((validate_min && value < pt->min) ||
	    (validate_max && value > pt->max)) {
		NL_SET_ERR_MSG_ATTR(extack, nla,
				    "integer out of range");
		return -ERANGE;
	}

	return 0;
}