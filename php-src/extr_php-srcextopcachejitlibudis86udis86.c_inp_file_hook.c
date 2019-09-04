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
struct ud {int /*<<< orphan*/  inp_file; } ;

/* Variables and functions */
 int fgetc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
inp_file_hook(struct ud* u)
{
  return fgetc(u->inp_file);
}