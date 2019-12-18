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
typedef  int Oid ;

/* Variables and functions */
#define  DATEOID 132 
 unsigned int SQL3_DDT_DATE ; 
 unsigned int SQL3_DDT_ILLEGAL ; 
 unsigned int SQL3_DDT_TIME ; 
 unsigned int SQL3_DDT_TIMESTAMP ; 
 unsigned int SQL3_DDT_TIMESTAMP_WITH_TIME_ZONE ; 
 unsigned int SQL3_DDT_TIME_WITH_TIME_ZONE ; 
#define  TIMEOID 131 
#define  TIMESTAMPOID 130 
#define  TIMESTAMPTZOID 129 
#define  TIMETZOID 128 

__attribute__((used)) static unsigned int
ecpg_dynamic_type_DDT(Oid type)
{
	switch (type)
	{
		case DATEOID:
			return SQL3_DDT_DATE;
		case TIMEOID:
			return SQL3_DDT_TIME;
		case TIMESTAMPOID:
			return SQL3_DDT_TIMESTAMP;
		case TIMESTAMPTZOID:
			return SQL3_DDT_TIMESTAMP_WITH_TIME_ZONE;
		case TIMETZOID:
			return SQL3_DDT_TIME_WITH_TIME_ZONE;
		default:
			return SQL3_DDT_ILLEGAL;
	}
}