#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int efd; int /*<<< orphan*/  mode; int /*<<< orphan*/  cbt; scalar_t__ aio_ctx; } ;
typedef  TYPE_1__ afalg_aio ;

/* Variables and functions */
 int /*<<< orphan*/  AFALG_F_AFALG_INIT_AIO ; 
 int /*<<< orphan*/  AFALG_R_IO_SETUP_FAILED ; 
 int /*<<< orphan*/  AFALGerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALG_PERR (char*,char*,int) ; 
 int /*<<< orphan*/  MAX_INFLIGHTS ; 
 int /*<<< orphan*/  MODE_UNINIT ; 
 int io_setup (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int afalg_init_aio(afalg_aio *aio)
{
    int r = -1;

    /* Initialise for AIO */
    aio->aio_ctx = 0;
    r = io_setup(MAX_INFLIGHTS, &aio->aio_ctx);
    if (r < 0) {
        ALG_PERR("%s(%d): io_setup error : ", __FILE__, __LINE__);
        AFALGerr(AFALG_F_AFALG_INIT_AIO, AFALG_R_IO_SETUP_FAILED);
        return 0;
    }

    memset(aio->cbt, 0, sizeof(aio->cbt));
    aio->efd = -1;
    aio->mode = MODE_UNINIT;

    return 1;
}