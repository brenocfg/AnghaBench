#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int shmem_fallback; scalar_t__ hdc; scalar_t__ base_cx; scalar_t__ base_cy; scalar_t__ using_shtex; } ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ INIT_SHTEX_FAILED ; 
 scalar_t__ capture_ready () ; 
 scalar_t__ capture_should_init () ; 
 scalar_t__ capture_should_stop () ; 
 TYPE_1__ data ; 
 scalar_t__ functions_initialized ; 
 int /*<<< orphan*/  get_window_size (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  glGetError () ; 
 int /*<<< orphan*/  gl_free () ; 
 scalar_t__ gl_init (scalar_t__) ; 
 int /*<<< orphan*/  gl_shmem_capture () ; 
 int /*<<< orphan*/  gl_shtex_capture () ; 
 scalar_t__ init_gl_functions () ; 

__attribute__((used)) static void gl_capture(HDC hdc)
{
	static bool critical_failure = false;

	if (critical_failure) {
		return;
	}

	if (!functions_initialized) {
		functions_initialized = init_gl_functions();
		if (!functions_initialized) {
			critical_failure = true;
			return;
		}
	}

	/* reset error flag */
	glGetError();

	if (capture_should_stop()) {
		gl_free();
	}
	if (capture_should_init()) {
		if (gl_init(hdc) == INIT_SHTEX_FAILED) {
			data.shmem_fallback = true;
			gl_init(hdc);
		}
	}
	if (capture_ready() && hdc == data.hdc) {
		uint32_t new_cx;
		uint32_t new_cy;

		/* reset capture if resized */
		get_window_size(hdc, &new_cx, &new_cy);
		if (new_cx != data.base_cx || new_cy != data.base_cy) {
			if (new_cx != 0 && new_cy != 0)
				gl_free();
			return;
		}

		if (data.using_shtex)
			gl_shtex_capture();
		else
			gl_shmem_capture();
	}
}