#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* img_comp; TYPE_1__* s; } ;
typedef  TYPE_3__ stbi__jpeg ;
struct TYPE_6__ {int /*<<< orphan*/ * linebuf; scalar_t__ coeff; int /*<<< orphan*/ * raw_coeff; int /*<<< orphan*/ * data; int /*<<< orphan*/ * raw_data; } ;
struct TYPE_5__ {int img_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stbi__cleanup_jpeg(stbi__jpeg *j)
{
   int i;
   for (i=0; i < j->s->img_n; ++i) {
      if (j->img_comp[i].raw_data) {
         STBI_FREE(j->img_comp[i].raw_data);
         j->img_comp[i].raw_data = NULL;
         j->img_comp[i].data = NULL;
      }
      if (j->img_comp[i].raw_coeff) {
         STBI_FREE(j->img_comp[i].raw_coeff);
         j->img_comp[i].raw_coeff = 0;
         j->img_comp[i].coeff = 0;
      }
      if (j->img_comp[i].linebuf) {
         STBI_FREE(j->img_comp[i].linebuf);
         j->img_comp[i].linebuf = NULL;
      }
   }
}