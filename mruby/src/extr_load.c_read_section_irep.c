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
struct rite_section_irep_header {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int /*<<< orphan*/ * read_irep_record (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_irep*
read_section_irep(mrb_state *mrb, const uint8_t *bin, uint8_t flags)
{
  size_t len;

  bin += sizeof(struct rite_section_irep_header);
  return read_irep_record(mrb, bin, &len, flags);
}