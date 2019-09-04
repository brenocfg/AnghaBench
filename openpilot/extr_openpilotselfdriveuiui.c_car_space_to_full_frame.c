#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* v; } ;
typedef  TYPE_2__ vec4 ;
struct TYPE_13__ {int member_0; int member_1; int member_2; } ;
struct TYPE_15__ {int* v; TYPE_1__ member_0; } ;
typedef  TYPE_3__ const vec3 ;
struct TYPE_17__ {int /*<<< orphan*/  extrinsic_matrix; } ;
struct TYPE_16__ {TYPE_5__ scene; } ;
typedef  TYPE_4__ UIState ;
typedef  TYPE_5__ UIScene ;

/* Variables and functions */
 int /*<<< orphan*/  intrinsic_matrix ; 
 TYPE_2__ matvecmul (int /*<<< orphan*/ ,TYPE_2__) ; 
 TYPE_3__ const matvecmul3 (int /*<<< orphan*/ ,TYPE_3__ const) ; 

vec3 car_space_to_full_frame(const UIState *s, vec4 car_space_projective) {
  const UIScene *scene = &s->scene;

  // We'll call the car space point p.
  // First project into normalized image coordinates with the extrinsics matrix.
  const vec4 Ep4 = matvecmul(scene->extrinsic_matrix, car_space_projective);

  // The last entry is zero because of how we store E (to use matvecmul).
  const vec3 Ep = {{Ep4.v[0], Ep4.v[1], Ep4.v[2]}};
  const vec3 KEp = matvecmul3(intrinsic_matrix, Ep);

  // Project.
  const vec3 p_image = {{KEp.v[0] / KEp.v[2], KEp.v[1] / KEp.v[2], 1.}};
  return p_image;
}