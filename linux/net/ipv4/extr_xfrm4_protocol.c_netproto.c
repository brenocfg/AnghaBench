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
struct net_protocol {int dummy; } ;

/* Variables and functions */
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 
 struct net_protocol const ah4_protocol ; 
 struct net_protocol const esp4_protocol ; 
 struct net_protocol const ipcomp4_protocol ; 

__attribute__((used)) static inline const struct net_protocol *netproto(unsigned char protocol)
{
	switch (protocol) {
	case IPPROTO_ESP:
		return &esp4_protocol;
	case IPPROTO_AH:
		return &ah4_protocol;
	case IPPROTO_COMP:
		return &ipcomp4_protocol;
	}

	return NULL;
}