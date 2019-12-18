#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct data_buf {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {size_t bwi; int /*<<< orphan*/  ps; struct data_buf* bufs; } ;

/* Variables and functions */
 scalar_t__ BUF_SIZE ; 
 TYPE_1__ ub ; 

__attribute__((used)) static void add_byte(uint8_t byte) {
  struct data_buf *buf = &ub.bufs[ub.bwi];
  if (buf->len < BUF_SIZE) {
    buf->data[buf->len++] = byte;
    ub.ps++;
  }
}