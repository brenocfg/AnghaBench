#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {float x0; float x1; } ;
struct TYPE_18__ {scalar_t__ prevGlyphIndex; int codepoint; char const* str; char* next; float x; float nextx; } ;
struct TYPE_17__ {float devicePxRatio; int /*<<< orphan*/  fs; } ;
struct TYPE_16__ {scalar_t__ fontId; float fontSize; float letterSpacing; float fontBlur; int /*<<< orphan*/  textAlign; } ;
struct TYPE_15__ {char const* start; char const* end; float width; float minx; float maxx; char* next; } ;
typedef  TYPE_1__ NVGtextRow ;
typedef  TYPE_2__ NVGstate ;
typedef  TYPE_3__ NVGcontext ;
typedef  TYPE_4__ FONStextIter ;
typedef  TYPE_5__ FONSquad ;

/* Variables and functions */
 scalar_t__ FONS_INVALID ; 
 int NVG_CHAR ; 
 int NVG_NEWLINE ; 
 int NVG_SPACE ; 
 int /*<<< orphan*/  fonsSetAlign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fonsSetBlur (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetFont (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fonsSetSize (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetSpacing (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsTextIterInit (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ fonsTextIterNext (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ nvg__allocTextAtlas (TYPE_3__*) ; 
 float nvg__getFontScale (TYPE_2__*) ; 
 TYPE_2__* nvg__getState (TYPE_3__*) ; 
 int strlen (char const*) ; 

int nvgTextBreakLines(NVGcontext* ctx, const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows)
{
	NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	FONStextIter iter, prevIter;
	FONSquad q;
	int nrows = 0;
	float rowStartX = 0;
	float rowWidth = 0;
	float rowMinX = 0;
	float rowMaxX = 0;
	const char* rowStart = NULL;
	const char* rowEnd = NULL;
	const char* wordStart = NULL;
	float wordStartX = 0;
	float wordMinX = 0;
	const char* breakEnd = NULL;
	float breakWidth = 0;
	float breakMaxX = 0;
	int type = NVG_SPACE, ptype = NVG_SPACE;
	unsigned int pcodepoint = 0;

	if (maxRows == 0) return 0;
	if (state->fontId == FONS_INVALID) return 0;

	if (end == NULL)
		end = string + strlen(string);

	if (string == end) return 0;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	breakRowWidth *= scale;

	fonsTextIterInit(ctx->fs, &iter, 0, 0, string, end);
	prevIter = iter;
	while (fonsTextIterNext(ctx->fs, &iter, &q)) {
		if (iter.prevGlyphIndex < 0 && nvg__allocTextAtlas(ctx)) { // can not retrieve glyph?
			iter = prevIter;
			fonsTextIterNext(ctx->fs, &iter, &q); // try again
		}
		prevIter = iter;
		switch (iter.codepoint) {
			case 9:			// \t
			case 11:		// \v
			case 12:		// \f
			case 32:		// space
			case 0x00a0:	// NBSP
				type = NVG_SPACE;
				break;
			case 10:		// \n
				type = pcodepoint == 13 ? NVG_SPACE : NVG_NEWLINE;
				break;
			case 13:		// \r
				type = pcodepoint == 10 ? NVG_SPACE : NVG_NEWLINE;
				break;
			case 0x0085:	// NEL
				type = NVG_NEWLINE;
				break;
			default:
				type = NVG_CHAR;
				break;
		}

		if (type == NVG_NEWLINE) {
			// Always handle new lines.
			rows[nrows].start = rowStart != NULL ? rowStart : iter.str;
			rows[nrows].end = rowEnd != NULL ? rowEnd : iter.str;
			rows[nrows].width = rowWidth * invscale;
			rows[nrows].minx = rowMinX * invscale;
			rows[nrows].maxx = rowMaxX * invscale;
			rows[nrows].next = iter.next;
			nrows++;
			if (nrows >= maxRows)
				return nrows;
			// Set null break point
			breakEnd = rowStart;
			breakWidth = 0.0;
			breakMaxX = 0.0;
			// Indicate to skip the white space at the beginning of the row.
			rowStart = NULL;
			rowEnd = NULL;
			rowWidth = 0;
			rowMinX = rowMaxX = 0;
		} else {
			if (rowStart == NULL) {
				// Skip white space until the beginning of the line
				if (type == NVG_CHAR) {
					// The current char is the row so far
					rowStartX = iter.x;
					rowStart = iter.str;
					rowEnd = iter.next;
					rowWidth = iter.nextx - rowStartX; // q.x1 - rowStartX;
					rowMinX = q.x0 - rowStartX;
					rowMaxX = q.x1 - rowStartX;
					wordStart = iter.str;
					wordStartX = iter.x;
					wordMinX = q.x0 - rowStartX;
					// Set null break point
					breakEnd = rowStart;
					breakWidth = 0.0;
					breakMaxX = 0.0;
				}
			} else {
				float nextWidth = iter.nextx - rowStartX;

				// track last non-white space character
				if (type == NVG_CHAR) {
					rowEnd = iter.next;
					rowWidth = iter.nextx - rowStartX;
					rowMaxX = q.x1 - rowStartX;
				}
				// track last end of a word
				if (ptype == NVG_CHAR && type == NVG_SPACE) {
					breakEnd = iter.str;
					breakWidth = rowWidth;
					breakMaxX = rowMaxX;
				}
				// track last beginning of a word
				if (ptype == NVG_SPACE && type == NVG_CHAR) {
					wordStart = iter.str;
					wordStartX = iter.x;
					wordMinX = q.x0 - rowStartX;
				}

				// Break to new line when a character is beyond break width.
				if (type == NVG_CHAR && nextWidth > breakRowWidth) {
					// The run length is too long, need to break to new line.
					if (breakEnd == rowStart) {
						// The current word is longer than the row length, just break it from here.
						rows[nrows].start = rowStart;
						rows[nrows].end = iter.str;
						rows[nrows].width = rowWidth * invscale;
						rows[nrows].minx = rowMinX * invscale;
						rows[nrows].maxx = rowMaxX * invscale;
						rows[nrows].next = iter.str;
						nrows++;
						if (nrows >= maxRows)
							return nrows;
						rowStartX = iter.x;
						rowStart = iter.str;
						rowEnd = iter.next;
						rowWidth = iter.nextx - rowStartX;
						rowMinX = q.x0 - rowStartX;
						rowMaxX = q.x1 - rowStartX;
						wordStart = iter.str;
						wordStartX = iter.x;
						wordMinX = q.x0 - rowStartX;
					} else {
						// Break the line from the end of the last word, and start new line from the beginning of the new.
						rows[nrows].start = rowStart;
						rows[nrows].end = breakEnd;
						rows[nrows].width = breakWidth * invscale;
						rows[nrows].minx = rowMinX * invscale;
						rows[nrows].maxx = breakMaxX * invscale;
						rows[nrows].next = wordStart;
						nrows++;
						if (nrows >= maxRows)
							return nrows;
						rowStartX = wordStartX;
						rowStart = wordStart;
						rowEnd = iter.next;
						rowWidth = iter.nextx - rowStartX;
						rowMinX = wordMinX;
						rowMaxX = q.x1 - rowStartX;
						// No change to the word start
					}
					// Set null break point
					breakEnd = rowStart;
					breakWidth = 0.0;
					breakMaxX = 0.0;
				}
			}
		}

		pcodepoint = iter.codepoint;
		ptype = type;
	}

	// Break the line from the end of the last word, and start new line from the beginning of the new.
	if (rowStart != NULL) {
		rows[nrows].start = rowStart;
		rows[nrows].end = rowEnd;
		rows[nrows].width = rowWidth * invscale;
		rows[nrows].minx = rowMinX * invscale;
		rows[nrows].maxx = rowMaxX * invscale;
		rows[nrows].next = end;
		nrows++;
	}

	return nrows;
}