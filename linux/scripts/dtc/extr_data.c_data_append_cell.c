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
typedef  int /*<<< orphan*/  word ;
struct data {int dummy; } ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 struct data data_append_integer (struct data,int /*<<< orphan*/ ,int) ; 

struct data data_append_cell(struct data d, cell_t word)
{
	return data_append_integer(d, word, sizeof(word) * 8);
}