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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 
 int /*<<< orphan*/  SADB_SATYPE_AH ; 
 int /*<<< orphan*/  SADB_SATYPE_ESP ; 
 int /*<<< orphan*/  SADB_X_SATYPE_IPCOMP ; 

__attribute__((used)) static uint8_t
pfkey_proto2satype(uint16_t proto)
{
	switch (proto) {
	case IPPROTO_AH:
		return SADB_SATYPE_AH;
	case IPPROTO_ESP:
		return SADB_SATYPE_ESP;
	case IPPROTO_COMP:
		return SADB_X_SATYPE_IPCOMP;
	default:
		return 0;
	}
	/* NOTREACHED */
}