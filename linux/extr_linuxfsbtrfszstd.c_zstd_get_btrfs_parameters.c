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
struct TYPE_5__ {scalar_t__ windowLog; } ;
struct TYPE_6__ {TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZSTD_BTRFS_DEFAULT_LEVEL ; 
 size_t ZSTD_BTRFS_MAX_INPUT ; 
 scalar_t__ ZSTD_BTRFS_MAX_WINDOWLOG ; 
 TYPE_2__ ZSTD_getParams (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ZSTD_parameters zstd_get_btrfs_parameters(size_t src_len)
{
	ZSTD_parameters params = ZSTD_getParams(ZSTD_BTRFS_DEFAULT_LEVEL,
						src_len, 0);

	if (params.cParams.windowLog > ZSTD_BTRFS_MAX_WINDOWLOG)
		params.cParams.windowLog = ZSTD_BTRFS_MAX_WINDOWLOG;
	WARN_ON(src_len > ZSTD_BTRFS_MAX_INPUT);
	return params;
}