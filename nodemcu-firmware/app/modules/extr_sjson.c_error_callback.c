#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct jsonsl_state_st {int dummy; } ;
typedef  TYPE_1__* jsonsl_t ;
typedef  int /*<<< orphan*/  jsonsl_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  error; int /*<<< orphan*/  complete; } ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_2__ JSN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  jsonsl_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int error_callback(jsonsl_t jsn,
                   jsonsl_error_t err,
                   struct jsonsl_state_st *state,
                   char *at)
{
  JSN_DATA *data = (JSN_DATA *) jsn->data;
  if (!data->complete) {
    data->error = jsonsl_strerror(err);
  }

  //fprintf(stderr, "Got error at pos %lu: %s\n", jsn->pos, jsonsl_strerror(err));
  return 0;
}