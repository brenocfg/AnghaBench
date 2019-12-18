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
struct tilegx_spr {int number; char const* name; } ;

/* Variables and functions */
 void* bsearch (void const*,void const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilegx_num_sprs ; 
 int /*<<< orphan*/  tilegx_spr_compare ; 
 scalar_t__ tilegx_sprs ; 

const char *
get_tilegx_spr_name (int num)
{
  void *result;
  struct tilegx_spr key;

  key.number = num;
  result = bsearch((const void *) &key, (const void *) tilegx_sprs,
                   tilegx_num_sprs, sizeof (struct tilegx_spr),
                   tilegx_spr_compare);

  if (result == NULL)
  {
    return (NULL);
  }
  else
  {
    struct tilegx_spr *result_ptr = (struct tilegx_spr *) result;
    return (result_ptr->name);
  }
}