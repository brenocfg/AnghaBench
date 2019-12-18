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
typedef  unsigned long long u64 ;
struct hdspm {int io_type; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 unsigned long long div_u64 (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static u64 hdspm_calc_dds_value(struct hdspm *hdspm, u64 period)
{
	u64 freq_const;

	if (period == 0)
		return 0;

	switch (hdspm->io_type) {
	case MADI:
	case AES32:
		freq_const = 110069313433624ULL;
		break;
	case RayDAT:
	case AIO:
		freq_const = 104857600000000ULL;
		break;
	case MADIface:
		freq_const = 131072000000000ULL;
		break;
	default:
		snd_BUG();
		return 0;
	}

	return div_u64(freq_const, period);
}