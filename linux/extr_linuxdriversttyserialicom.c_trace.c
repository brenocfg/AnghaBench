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
struct icom_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void trace(struct icom_port *icom_port, char *trace_pt, unsigned long trace_data) {}