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

/* Variables and functions */
 int /*<<< orphan*/  bsd_compress (void*,unsigned char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bsd_incomp (void *state, unsigned char *ibuf, int icnt)
  {
    (void) bsd_compress (state, ibuf, (char *) 0, icnt, 0);
  }