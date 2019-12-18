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
struct ak4117 {unsigned char (* read ) (int /*<<< orphan*/ ,unsigned char) ;int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 unsigned char stub1 (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static inline unsigned char reg_read(struct ak4117 *ak4117, unsigned char reg)
{
	return ak4117->read(ak4117->private_data, reg);
}