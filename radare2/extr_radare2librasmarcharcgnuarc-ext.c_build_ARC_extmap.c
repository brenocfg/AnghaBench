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

void
build_ARC_extmap (void *text_bfd)
{
#if 0
  asection *sect;

  /* the map is built each time gdb loads an executable file - so free any
   * existing map, as the map defined by the new file may differ from the old
   */
  destroy_map();

  for (sect = text_bfd->sections; sect != NULL; sect = sect->next)
    if (!strncmp (sect->name,
                  ".gnu.linkonce.arcextmap.",
          sizeof (".gnu.linkonce.arcextmap.") - 1)
        || !strcmp (sect->name,".arcextmap"))
      {
        bfd_size_type  count  = bfd_get_section_size (sect);
        unsigned char* buffer = xmalloc (count);

        if (buffer)
          {
            if (bfd_get_section_contents (text_bfd, sect, buffer, 0, count))
              create_map(buffer, count);
            free (buffer);
          }
      }
#endif
}