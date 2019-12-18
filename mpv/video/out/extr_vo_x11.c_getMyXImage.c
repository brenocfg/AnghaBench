#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* x11; } ;
struct TYPE_9__ {int /*<<< orphan*/  visual; } ;
struct priv {int Shmem_Flag; int image_height; TYPE_3__** myximage; int /*<<< orphan*/  image_width; int /*<<< orphan*/  depth; TYPE_2__ vinfo; TYPE_4__* Shminfo; struct vo* vo; } ;
struct TYPE_11__ {scalar_t__ shmid; char* shmaddr; int /*<<< orphan*/  readOnly; } ;
struct TYPE_10__ {int bytes_per_line; int height; char* data; } ;
struct TYPE_8__ {int /*<<< orphan*/  display; scalar_t__ ShmCompletionEvent; scalar_t__ display_is_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*) ; 
 scalar_t__ ShmCompletion ; 
 TYPE_3__* XCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyImage (TYPE_3__*) ; 
 int /*<<< orphan*/  XShmAttach (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_3__* XShmCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XShmGetEventBase (int /*<<< orphan*/ ) ; 
 scalar_t__ XShmQueryExtension (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPixmap ; 
 char* calloc (int,int) ; 
 scalar_t__ shmat (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ shmget (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool getMyXImage(struct priv *p, int foo)
{
    struct vo *vo = p->vo;
    if (vo->x11->display_is_local && XShmQueryExtension(vo->x11->display)) {
        p->Shmem_Flag = 1;
        vo->x11->ShmCompletionEvent = XShmGetEventBase(vo->x11->display)
                                    + ShmCompletion;
    } else {
        p->Shmem_Flag = 0;
        MP_WARN(vo, "Shared memory not supported\nReverting to normal Xlib\n");
    }

    if (p->Shmem_Flag) {
        p->myximage[foo] =
            XShmCreateImage(vo->x11->display, p->vinfo.visual, p->depth,
                            ZPixmap, NULL, &p->Shminfo[foo], p->image_width,
                            p->image_height);
        if (p->myximage[foo] == NULL) {
            MP_WARN(vo, "Shared memory error,disabling ( Ximage error )\n");
            goto shmemerror;
        }
        p->Shminfo[foo].shmid = shmget(IPC_PRIVATE,
                                       p->myximage[foo]->bytes_per_line *
                                       p->myximage[foo]->height,
                                       IPC_CREAT | 0777);
        if (p->Shminfo[foo].shmid < 0) {
            XDestroyImage(p->myximage[foo]);
            MP_WARN(vo, "Shared memory error,disabling ( seg id error )\n");
            goto shmemerror;
        }
        p->Shminfo[foo].shmaddr = (char *) shmat(p->Shminfo[foo].shmid, 0, 0);

        if (p->Shminfo[foo].shmaddr == ((char *) -1)) {
            XDestroyImage(p->myximage[foo]);
            MP_WARN(vo, "Shared memory error,disabling ( address error )\n");
            goto shmemerror;
        }
        p->myximage[foo]->data = p->Shminfo[foo].shmaddr;
        p->Shminfo[foo].readOnly = False;
        XShmAttach(vo->x11->display, &p->Shminfo[foo]);

        XSync(vo->x11->display, False);

        shmctl(p->Shminfo[foo].shmid, IPC_RMID, 0);
    } else {
shmemerror:
        p->Shmem_Flag = 0;

        MP_VERBOSE(vo, "Not using SHM.\n");
        p->myximage[foo] =
            XCreateImage(vo->x11->display, p->vinfo.visual, p->depth, ZPixmap,
                         0, NULL, p->image_width, p->image_height, 8, 0);
        if (!p->myximage[foo]) {
            MP_WARN(vo, "could not allocate image");
            return false;
        }
        p->myximage[foo]->data =
            calloc(1, p->myximage[foo]->bytes_per_line * p->image_height + 32);
    }
    return true;
}