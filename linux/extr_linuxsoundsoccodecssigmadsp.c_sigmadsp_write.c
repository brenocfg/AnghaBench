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
struct sigmadsp {int (* write ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int sigmadsp_write(struct sigmadsp *sigmadsp, unsigned int addr,
	const uint8_t data[], size_t len)
{
	return sigmadsp->write(sigmadsp->control_data, addr, data, len);
}