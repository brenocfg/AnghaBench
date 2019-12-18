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
typedef  scalar_t__ uint16_t ;
struct rite_section_header {int /*<<< orphan*/  section_size; int /*<<< orphan*/  section_ident; } ;
struct rite_binary_header {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  RITE_BINARY_EOF ; 
 int /*<<< orphan*/  RITE_SECTION_DEBUG_IDENT ; 
 int /*<<< orphan*/  RITE_SECTION_IREP_IDENT ; 
 int /*<<< orphan*/  RITE_SECTION_LV_IDENT ; 
 int /*<<< orphan*/  bin_to_uint32 (int /*<<< orphan*/ ) ; 
 scalar_t__ calc_crc_16_ccitt (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t offset_crc_body () ; 
 int read_binary_header (int /*<<< orphan*/  const*,size_t,size_t*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int read_section_debug (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_section_irep (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int read_section_lv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_irep*
read_irep(mrb_state *mrb, const uint8_t *bin, size_t bufsize, uint8_t flags)
{
  int result;
  mrb_irep *irep = NULL;
  const struct rite_section_header *section_header;
  uint16_t crc;
  size_t bin_size = 0;
  size_t n;

  if ((mrb == NULL) || (bin == NULL)) {
    return NULL;
  }

  result = read_binary_header(bin, bufsize, &bin_size, &crc, &flags);
  if (result != MRB_DUMP_OK) {
    return NULL;
  }

  n = offset_crc_body();
  if (crc != calc_crc_16_ccitt(bin + n, bin_size - n, 0)) {
    return NULL;
  }

  bin += sizeof(struct rite_binary_header);
  do {
    section_header = (const struct rite_section_header *)bin;
    if (memcmp(section_header->section_ident, RITE_SECTION_IREP_IDENT, sizeof(section_header->section_ident)) == 0) {
      irep = read_section_irep(mrb, bin, flags);
      if (!irep) return NULL;
    }
    else if (memcmp(section_header->section_ident, RITE_SECTION_DEBUG_IDENT, sizeof(section_header->section_ident)) == 0) {
      if (!irep) return NULL;   /* corrupted data */
      result = read_section_debug(mrb, bin, irep, flags);
      if (result < MRB_DUMP_OK) {
        return NULL;
      }
    }
    else if (memcmp(section_header->section_ident, RITE_SECTION_LV_IDENT, sizeof(section_header->section_ident)) == 0) {
      if (!irep) return NULL;
      result = read_section_lv(mrb, bin, irep, flags);
      if (result < MRB_DUMP_OK) {
        return NULL;
      }
    }
    bin += bin_to_uint32(section_header->section_size);
  } while (memcmp(section_header->section_ident, RITE_BINARY_EOF, sizeof(section_header->section_ident)) != 0);

  return irep;
}