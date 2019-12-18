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
struct xvctx {int Shmem_Flag; int /*<<< orphan*/  image_height; TYPE_1__** xvimage; int /*<<< orphan*/  xv_format; int /*<<< orphan*/  xv_port; TYPE_2__* Shminfo; int /*<<< orphan*/  image_width; } ;
struct vo_x11_state {int /*<<< orphan*/  display; scalar_t__ ShmCompletionEvent; scalar_t__ display_is_local; } ;
struct vo {struct vo_x11_state* x11; struct xvctx* priv; } ;
struct mp_image {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_4__ {void* data; int width; int height; int /*<<< orphan*/  data_size; } ;
typedef  TYPE_1__ XvImage ;
struct TYPE_5__ {void* shmaddr; int /*<<< orphan*/  shmid; int /*<<< orphan*/  readOnly; } ;

/* Variables and functions */
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  False ; 
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_INFO (struct vo*,char*) ; 
 scalar_t__ ShmCompletion ; 
 int /*<<< orphan*/  XShmAttach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ XShmGetEventBase (int /*<<< orphan*/ ) ; 
 scalar_t__ XShmQueryExtension (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XvCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ XvShmCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,TYPE_2__*) ; 
 void* av_malloc (int /*<<< orphan*/ ) ; 
 struct mp_image get_xv_buffer (struct vo*,int) ; 
 int /*<<< orphan*/  mp_image_clear (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int,int) ; 
 void* shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool allocate_xvimage(struct vo *vo, int foo)
{
    struct xvctx *ctx = vo->priv;
    struct vo_x11_state *x11 = vo->x11;
    // align it for faster OSD rendering (draw_bmp.c swscale usage)
    int aligned_w = FFALIGN(ctx->image_width, 32);
    // round up the height to next chroma boundary too
    int aligned_h = FFALIGN(ctx->image_height, 2);
    if (x11->display_is_local && XShmQueryExtension(x11->display)) {
        ctx->Shmem_Flag = 1;
        x11->ShmCompletionEvent = XShmGetEventBase(x11->display)
                                + ShmCompletion;
    } else {
        ctx->Shmem_Flag = 0;
        MP_INFO(vo, "Shared memory not supported\nReverting to normal Xv.\n");
    }
    if (ctx->Shmem_Flag) {
        ctx->xvimage[foo] =
            (XvImage *) XvShmCreateImage(x11->display, ctx->xv_port,
                                         ctx->xv_format, NULL,
                                         aligned_w, aligned_h,
                                         &ctx->Shminfo[foo]);
        if (!ctx->xvimage[foo])
            return false;

        ctx->Shminfo[foo].shmid = shmget(IPC_PRIVATE,
                                         ctx->xvimage[foo]->data_size,
                                         IPC_CREAT | 0777);
        ctx->Shminfo[foo].shmaddr = shmat(ctx->Shminfo[foo].shmid, 0, 0);
        if (ctx->Shminfo[foo].shmaddr == (void *)-1)
            return false;
        ctx->Shminfo[foo].readOnly = False;

        ctx->xvimage[foo]->data = ctx->Shminfo[foo].shmaddr;
        XShmAttach(x11->display, &ctx->Shminfo[foo]);
        XSync(x11->display, False);
        shmctl(ctx->Shminfo[foo].shmid, IPC_RMID, 0);
    } else {
        ctx->xvimage[foo] =
            (XvImage *) XvCreateImage(x11->display, ctx->xv_port,
                                      ctx->xv_format, NULL, aligned_w,
                                      aligned_h);
        if (!ctx->xvimage[foo])
            return false;
        ctx->xvimage[foo]->data = av_malloc(ctx->xvimage[foo]->data_size);
        if (!ctx->xvimage[foo]->data)
            return false;
        XSync(x11->display, False);
    }

    if ((ctx->xvimage[foo]->width < aligned_w) ||
        (ctx->xvimage[foo]->height < aligned_h)) {
        MP_ERR(vo, "Got XvImage with too small size: %ux%u (expected %ux%u)\n",
               ctx->xvimage[foo]->width, ctx->xvimage[foo]->height,
               aligned_w, ctx->image_height);
        return false;
    }

    struct mp_image img = get_xv_buffer(vo, foo);
    mp_image_set_size(&img, aligned_w, aligned_h);
    mp_image_clear(&img, 0, 0, img.w, img.h);
    return true;
}