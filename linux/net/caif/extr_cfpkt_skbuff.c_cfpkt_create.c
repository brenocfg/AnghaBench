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
typedef  scalar_t__ u16 ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 scalar_t__ PKT_POSTFIX ; 
 int /*<<< orphan*/  PKT_PREFIX ; 
 struct cfpkt* cfpkt_create_pfx (scalar_t__,int /*<<< orphan*/ ) ; 

inline struct cfpkt *cfpkt_create(u16 len)
{
	return cfpkt_create_pfx(len + PKT_POSTFIX, PKT_PREFIX);
}