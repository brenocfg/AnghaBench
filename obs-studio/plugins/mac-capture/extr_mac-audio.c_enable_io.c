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
struct coreaudio_data {int /*<<< orphan*/  unit; } ;
typedef  enum coreaudio_io_type { ____Placeholder_coreaudio_io_type } coreaudio_io_type ;
typedef  int /*<<< orphan*/  enable_int ;
typedef  int UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_INPUT ; 
 int /*<<< orphan*/  BUS_OUTPUT ; 
 int IO_TYPE_INPUT ; 
 int /*<<< orphan*/  SCOPE_INPUT ; 
 int /*<<< orphan*/  SCOPE_OUTPUT ; 
 int /*<<< orphan*/  kAudioOutputUnitProperty_EnableIO ; 
 int set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static inline bool enable_io(struct coreaudio_data *ca,
			     enum coreaudio_io_type type, bool enable)
{
	UInt32 enable_int = enable;
	return set_property(ca->unit, kAudioOutputUnitProperty_EnableIO,
			    (type == IO_TYPE_INPUT) ? SCOPE_INPUT
						    : SCOPE_OUTPUT,
			    (type == IO_TYPE_INPUT) ? BUS_INPUT : BUS_OUTPUT,
			    &enable_int, sizeof(enable_int));
}