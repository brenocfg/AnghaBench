#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_4__ {int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 scalar_t__ bfd_get_section_contents (void*,TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_section_size (TYPE_1__*) ; 
 int /*<<< orphan*/  create_map (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_map () ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 unsigned char* xmalloc (int /*<<< orphan*/ ) ; 

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