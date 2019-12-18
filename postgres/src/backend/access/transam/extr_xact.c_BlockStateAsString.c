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
typedef  int TBlockState ;

/* Variables and functions */
#define  TBLOCK_ABORT 147 
#define  TBLOCK_ABORT_END 146 
#define  TBLOCK_ABORT_PENDING 145 
#define  TBLOCK_BEGIN 144 
#define  TBLOCK_DEFAULT 143 
#define  TBLOCK_END 142 
#define  TBLOCK_IMPLICIT_INPROGRESS 141 
#define  TBLOCK_INPROGRESS 140 
#define  TBLOCK_PARALLEL_INPROGRESS 139 
#define  TBLOCK_PREPARE 138 
#define  TBLOCK_STARTED 137 
#define  TBLOCK_SUBABORT 136 
#define  TBLOCK_SUBABORT_END 135 
#define  TBLOCK_SUBABORT_PENDING 134 
#define  TBLOCK_SUBABORT_RESTART 133 
#define  TBLOCK_SUBBEGIN 132 
#define  TBLOCK_SUBCOMMIT 131 
#define  TBLOCK_SUBINPROGRESS 130 
#define  TBLOCK_SUBRELEASE 129 
#define  TBLOCK_SUBRESTART 128 

__attribute__((used)) static const char *
BlockStateAsString(TBlockState blockState)
{
	switch (blockState)
	{
		case TBLOCK_DEFAULT:
			return "DEFAULT";
		case TBLOCK_STARTED:
			return "STARTED";
		case TBLOCK_BEGIN:
			return "BEGIN";
		case TBLOCK_INPROGRESS:
			return "INPROGRESS";
		case TBLOCK_IMPLICIT_INPROGRESS:
			return "IMPLICIT_INPROGRESS";
		case TBLOCK_PARALLEL_INPROGRESS:
			return "PARALLEL_INPROGRESS";
		case TBLOCK_END:
			return "END";
		case TBLOCK_ABORT:
			return "ABORT";
		case TBLOCK_ABORT_END:
			return "ABORT_END";
		case TBLOCK_ABORT_PENDING:
			return "ABORT_PENDING";
		case TBLOCK_PREPARE:
			return "PREPARE";
		case TBLOCK_SUBBEGIN:
			return "SUBBEGIN";
		case TBLOCK_SUBINPROGRESS:
			return "SUBINPROGRESS";
		case TBLOCK_SUBRELEASE:
			return "SUBRELEASE";
		case TBLOCK_SUBCOMMIT:
			return "SUBCOMMIT";
		case TBLOCK_SUBABORT:
			return "SUBABORT";
		case TBLOCK_SUBABORT_END:
			return "SUBABORT_END";
		case TBLOCK_SUBABORT_PENDING:
			return "SUBABORT_PENDING";
		case TBLOCK_SUBRESTART:
			return "SUBRESTART";
		case TBLOCK_SUBABORT_RESTART:
			return "SUBABORT_RESTART";
	}
	return "UNRECOGNIZED";
}