#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ engaged; } ;
struct TYPE_5__ {int /*<<< orphan*/ * track_vertices; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int /*<<< orphan*/  update_track_data (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_all_track_data(UIState *s) {
  const UIScene *scene = &s->scene;
  // Draw vision path
  update_track_data(s, false, &s->track_vertices[0]);

  if (scene->engaged) {
    // Draw MPC path when engaged
    update_track_data(s, true, &s->track_vertices[1]);
  }
}