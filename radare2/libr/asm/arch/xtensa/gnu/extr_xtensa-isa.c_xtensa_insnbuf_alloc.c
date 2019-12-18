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
typedef  int /*<<< orphan*/  xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_insnbuf_word ;
typedef  int /*<<< orphan*/  xtensa_insnbuf ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int xtensa_insnbuf_size (int /*<<< orphan*/ ) ; 

xtensa_insnbuf
xtensa_insnbuf_alloc (xtensa_isa isa)
{
  xtensa_insnbuf result = (xtensa_insnbuf)
    malloc (xtensa_insnbuf_size (isa) * sizeof (xtensa_insnbuf_word));
  CHECK_ALLOC (result, 0);
  return result;
}