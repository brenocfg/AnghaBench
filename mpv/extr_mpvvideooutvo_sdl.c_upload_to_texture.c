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
struct vo {struct priv* priv; } ;
struct TYPE_2__ {scalar_t__ sdl; } ;
struct priv {TYPE_1__ osd_format; } ;
typedef  int /*<<< orphan*/  SDL_Texture ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  SDL_ConvertPixels (int,int,scalar_t__,void*,int,scalar_t__,void*,int) ; 
 scalar_t__ SDL_LockTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int*) ; 
 scalar_t__ SDL_PIXELFORMAT_ARGB8888 ; 
 int /*<<< orphan*/  SDL_UnlockTexture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_UpdateTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static inline void upload_to_texture(struct vo *vo, SDL_Texture *tex,
                                     int w, int h, void *bitmap, int stride)
{
    struct priv *vc = vo->priv;

    if (vc->osd_format.sdl == SDL_PIXELFORMAT_ARGB8888) {
        // NOTE: this optimization is questionable, because SDL docs say
        // that this way is slow.
        // It did measure up faster, though...
        SDL_UpdateTexture(tex, NULL, bitmap, stride);
        return;
    }

    void *pixels;
    int pitch;
    if (SDL_LockTexture(tex, NULL, &pixels, &pitch)) {
        MP_ERR(vo, "Could not lock texture\n");
    } else {
        SDL_ConvertPixels(w, h, SDL_PIXELFORMAT_ARGB8888,
                          bitmap, stride,
                          vc->osd_format.sdl,
                          pixels, pitch);
        SDL_UnlockTexture(tex);
    }
}