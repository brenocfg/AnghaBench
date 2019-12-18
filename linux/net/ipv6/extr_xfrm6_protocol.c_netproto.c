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
struct inet6_protocol {int dummy; } ;

/* Variables and functions */
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 
 struct inet6_protocol const ah6_protocol ; 
 struct inet6_protocol const esp6_protocol ; 
 struct inet6_protocol const ipcomp6_protocol ; 

__attribute__((used)) static inline const struct inet6_protocol *netproto(unsigned char protocol)
{
	switch (protocol) {
	case IPPROTO_ESP:
		return &esp6_protocol;
	case IPPROTO_AH:
		return &ah6_protocol;
	case IPPROTO_COMP:
		return &ipcomp6_protocol;
	}

	return NULL;
}