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
struct via_clock {void* set_secondary_clock_state; void* set_primary_clock_state; int /*<<< orphan*/  set_engine_pll; void* set_engine_pll_state; int /*<<< orphan*/  set_secondary_pll; void* set_secondary_pll_state; void* set_secondary_clock_source; int /*<<< orphan*/  set_primary_pll; void* set_primary_pll_state; void* set_primary_clock_source; } ;

/* Variables and functions */
#define  UNICHROME_CLE266 140 
#define  UNICHROME_CN700 139 
#define  UNICHROME_CN750 138 
#define  UNICHROME_CX700 137 
#define  UNICHROME_K400 136 
#define  UNICHROME_K800 135 
#define  UNICHROME_K8M890 134 
#define  UNICHROME_P4M890 133 
#define  UNICHROME_P4M900 132 
#define  UNICHROME_PM800 131 
#define  UNICHROME_VX800 130 
#define  UNICHROME_VX855 129 
#define  UNICHROME_VX900 128 
 int /*<<< orphan*/  cle266_set_primary_pll ; 
 int /*<<< orphan*/  cle266_set_secondary_pll ; 
 void* dummy_set_clock_source ; 
 void* dummy_set_clock_state ; 
 int /*<<< orphan*/  dummy_set_pll ; 
 void* dummy_set_pll_state ; 
 int /*<<< orphan*/  k800_set_engine_pll ; 
 int /*<<< orphan*/  k800_set_primary_pll ; 
 int /*<<< orphan*/  k800_set_secondary_pll ; 
 scalar_t__ machine_is_olpc () ; 
 void* noop_set_clock_state ; 
 void* set_engine_pll_state ; 
 void* set_primary_clock_source ; 
 void* set_primary_clock_state ; 
 void* set_primary_pll_state ; 
 void* set_secondary_clock_source ; 
 void* set_secondary_clock_state ; 
 void* set_secondary_pll_state ; 
 int /*<<< orphan*/  vx855_set_engine_pll ; 
 int /*<<< orphan*/  vx855_set_primary_pll ; 
 int /*<<< orphan*/  vx855_set_secondary_pll ; 

void via_clock_init(struct via_clock *clock, int gfx_chip)
{
	switch (gfx_chip) {
	case UNICHROME_CLE266:
	case UNICHROME_K400:
		clock->set_primary_clock_state = dummy_set_clock_state;
		clock->set_primary_clock_source = dummy_set_clock_source;
		clock->set_primary_pll_state = dummy_set_pll_state;
		clock->set_primary_pll = cle266_set_primary_pll;

		clock->set_secondary_clock_state = dummy_set_clock_state;
		clock->set_secondary_clock_source = dummy_set_clock_source;
		clock->set_secondary_pll_state = dummy_set_pll_state;
		clock->set_secondary_pll = cle266_set_secondary_pll;

		clock->set_engine_pll_state = dummy_set_pll_state;
		clock->set_engine_pll = dummy_set_pll;
		break;
	case UNICHROME_K800:
	case UNICHROME_PM800:
	case UNICHROME_CN700:
	case UNICHROME_CX700:
	case UNICHROME_CN750:
	case UNICHROME_K8M890:
	case UNICHROME_P4M890:
	case UNICHROME_P4M900:
	case UNICHROME_VX800:
		clock->set_primary_clock_state = set_primary_clock_state;
		clock->set_primary_clock_source = set_primary_clock_source;
		clock->set_primary_pll_state = set_primary_pll_state;
		clock->set_primary_pll = k800_set_primary_pll;

		clock->set_secondary_clock_state = set_secondary_clock_state;
		clock->set_secondary_clock_source = set_secondary_clock_source;
		clock->set_secondary_pll_state = set_secondary_pll_state;
		clock->set_secondary_pll = k800_set_secondary_pll;

		clock->set_engine_pll_state = set_engine_pll_state;
		clock->set_engine_pll = k800_set_engine_pll;
		break;
	case UNICHROME_VX855:
	case UNICHROME_VX900:
		clock->set_primary_clock_state = set_primary_clock_state;
		clock->set_primary_clock_source = set_primary_clock_source;
		clock->set_primary_pll_state = set_primary_pll_state;
		clock->set_primary_pll = vx855_set_primary_pll;

		clock->set_secondary_clock_state = set_secondary_clock_state;
		clock->set_secondary_clock_source = set_secondary_clock_source;
		clock->set_secondary_pll_state = set_secondary_pll_state;
		clock->set_secondary_pll = vx855_set_secondary_pll;

		clock->set_engine_pll_state = set_engine_pll_state;
		clock->set_engine_pll = vx855_set_engine_pll;
		break;

	}

	if (machine_is_olpc()) {
		/* The OLPC XO-1.5 cannot suspend/resume reliably if the
		 * IGA1/IGA2 clocks are set as on or off (memory rot
		 * occasionally happens during suspend under such
		 * configurations).
		 *
		 * The only known stable scenario is to leave this bits as-is,
		 * which in their default states are documented to enable the
		 * clock only when it is needed.
		 */
		clock->set_primary_clock_state = noop_set_clock_state;
		clock->set_secondary_clock_state = noop_set_clock_state;
	}
}